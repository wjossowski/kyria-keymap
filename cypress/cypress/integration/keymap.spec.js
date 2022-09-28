it("exports keymap", () => {
  cy.visit("/splitkb/kyria/rev2/LAYOUT");

  cy.get("input[id=fileImport]").selectFile("/test_data/keymap.json", { force: true });
  cy.get("select[id=colorway-select]").select(27);

  cy.wait(2000);
  cy.get("button[id=printkeymaps]").click();
  cy.wait(2000);
  cy.get("div.layer.4")
    .not(".non-empty")
    .then(() => {
      cy.get(".backend-status").invoke("attr", "style", "display: none").should("have.attr", "style", "display: none");
      cy.get(".print-controls").invoke("attr", "style", "display: none").should("have.attr", "style", "display: none");
      cy.get(".meta-info").invoke("attr", "style", "display: none").should("have.attr", "style", "display: none");

      cy.get(".print-layout").screenshot(`keymap`);
      cy.get(".print-layout .layer-output").each((layout, index) => {
        cy.wrap(layout).screenshot(`layer_${index}`);
      });
    });
});
